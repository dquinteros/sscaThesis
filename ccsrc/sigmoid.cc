#include "sigmoid.h"

//Constructor Vacío
Sigmoid::Sigmoid(void)
{

}

//Constructor
Sigmoid::Sigmoid(int width, int height)
{
	this->width = width;
	this->height = height;
}

//Constructor Copia
Sigmoid::Sigmoid(const Sigmoid& s)
{
	this->A = s.A;
	this->B = s.B;
	this->width = s.width;
	this->height = s.height;
}

//Train Sigmoid Hsuan-Tien Lin 
void Sigmoid::SigmoidTrainLin(vector<float> deci,vector<bool> label,int prior1,int prior0)
{
	int maxiter = 100;
	double minstep = 1e-10;
	double sigma = 1e-12;



	double hiTarget = (prior1+1.0)/(prior1+2.0), loTarget = 1/(prior0+2.0);
	int len = prior1+prior0;
	vector<double> t(len,0.0);
	for (int i = 0; i < len; i++)
	{
		if (label[i] > 0){
			t[i]=hiTarget;
		}
		else{
			t[i]=loTarget;
		}
	}

	this->A=0.0;
	this->B=log((prior0+1.0)/(prior1+1.0));
	double fval = 0.0;
	double fApB;
	double p,q,d2,d1;
	for (int i = 0; i < len; i++)
	{
		fApB=deci[i]*A+B;
		if(fApB>=0){
			fval+=t[i]*fApB+log(1+exp(-fApB));
		}else{
			fval+=(t[i]-1)*fApB+log(1+exp(fApB));
		}
	}

	int it;
	for ( it = 0; it < maxiter; it++)
	{
		double h11 = sigma, h22 = sigma, h21=0.0, g1=0.0,g2=0.0;
		for (int i = 0; i < len; i++)
		{
			fApB = deci[i]*A+B;
			if (fApB >= 0)
				p=exp(-fApB)/(1.0+exp(-fApB)), q=1.0/(1.0+exp(-fApB));
			else
				p=1.0/(1.0+exp(fApB)), q=exp(fApB)/(1.0+exp(fApB));
			d2=p*q;
			h11 += deci[i]*deci[i]*d2, h22 += d2, h21 += deci[i]*d2;
			d1=t[i]-p;
			g1 += deci[i]*d1, g2 += d1;
		}
		if (abs(g1)<1e-5 && abs(g2)<1e-5) //Stopping criteria
			break;

		double det=h11*h22-h21*h21;
		double dA=-(h22*g1-h21*g2)/det, dB=-(-h21*g1+h11*g2)/det;
		double gd=g1*dA+g2*dB;
		double stepsize=1;

		while (stepsize >= minstep){ //Line search
			double newA=A+stepsize*dA, newB=B+stepsize*dB, newf=0.0;
			for (int i = 0; i < len; i++) {
				fApB=deci[i]*newA+newB;
				if (fApB >= 0)
					newf += t[i]*fApB+log(1+exp(-fApB));
				else
					newf += (t[i]-1)*fApB+log(1+exp(fApB));
			}

			if (newf<fval+0.0001*stepsize*gd){
				A=newA, B=newB, fval=newf;
				break; 
			}
			else{
				stepsize /= 2.0;
			}
		}

		if (stepsize < minstep){
			cout << "Line search fails" << endl;
			break;
		}	

	}
	if (it >= maxiter)
		cout << "Reaching maximum iterations" << endl;
}

//Train Sigmoid Jhon C. Platt (1999)
void Sigmoid::SigmoidTrain(vector<float> out,vector<bool> target,int prior1,int prior0)
{
	this->A = 0;
	this->B = log((prior0+1)/(prior1+1));
	double hiTarget = (prior1+1)/(prior1+2);
	double loTarget = 1/(prior0+2);
	double lambda = 1e-3;
	double olderr =  1e300;
	vector<double> pp (target.size(),(prior1+1)/(prior1+prior0+2));
	long count = 0;

	for (int i = 1; i <= 100; i++)
	{
		double t;
		double a=0,b=0,c=0,d=0,e=0;
		for (int it = 0; it < target.size(); it++)
		{
			if(target[it]){
				t = hiTarget;
			}
			else{
				t = loTarget;
			}

			double d1 = pp[it] - t;
			double d2 = pp[it] * (1-pp[it]);
			a += out[it] * out[it] * d2;
			b += d2;
			c += out[it] * d2;
			d += out[it] * d1;
			e += d1;
		}

		if(abs(d)<1e-9 && abs(e)<1e-9){
			break;
		}

		double oldA = this->A;
		double oldB = this->B;
		double err = 0;
		while(1) {
			double det = (a+lambda)*(b+lambda) - c * c;
			if(det == 0)
			{
				lambda *= 10;
				continue;
			}
			this->A = oldA + ((b+lambda) * d - c * e)/det;
			this->B = oldB + ((a+lambda) * e - c * d)/det;
			err = 0;
			for (int it = 0; it < out.size(); it++)
			{
				double p = 1/(1+exp(out[it] * A + B));
				pp[it] = p;
				if(p==0){
					err -= t * (-200) + (1-t) * log(1-p);
				}
				else if (p==1){
					err -= t * log(p) + (1-t) * (-200);
				}else{
					err -= t * log(p) + (1-t) * log(1-p);
				}
			}
			if(err < olderr * (1+1e-7))
			{
				lambda *= 0.1;
				break;
			}

			lambda *= 10;

			if(lambda >= 1e6){
				cout << "Something is broken!!" << endl;
				break;
			}
		}
		double diff = err-olderr;
		double scale = 0.5 * (err+olderr+1);
		if((diff > (-1e-3*scale)) && (diff < (1e-7*scale))){
			count++;
		}
		else{
			count = 0;
		}
		olderr = err;
		if (count == 3){
			break;
		}
	}

}

float Sigmoid::EvaluateSigmoid(float f)
{
	return 1.0/(1.0+exp(A*f+B));
}