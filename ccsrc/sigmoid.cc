#include "sigmoid.h"

//Constructor Vacío
Sigmoid::Sigmoid(void)
{

}

//Constructor Copia
Sigmoid::Sigmoid(Sigmoid s)
{
	this->A = s.A;
	this->B = s.B;
}

//Train Sigmoid Jhon C. Platt (1999)
void Sigmoid::SigmoidTrain(vector<float> out,vector<bool> target,int prior1,int prior0)
{
	A = 0;
	B = log((prior0+1)/(prior1+1));
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
		for (int i = 1; i <= out.size(); i++)
		{
			if(target[i])
				t = hiTarget;
			else
				t = loTarget;

			double d1 = pp[i] - t;
			double d2 = pp[i] * (1-pp[i]);
			a += out[i] * out[i] * d2;
			b += d2;
			c += out[i] * d2;
			d += out[i] * d1;
			e += d1;
		}

		if(abs(d)<1e-9 && abs(e)<1e-9)
			break;

		double oldA = A;
		double oldB = B;
		double err = 0;
		while(1) {
		    double det = (a+lambda)*(b+lambda) - c * c;
		    if(det == 0)
		    {
		    	lambda *= 10;
		    	continue;
		    }
		    A = oldA + ((b+lambda) * d - c * e)/det;
		    B = oldB + ((a+lambda) * e - c * d)/det;
		    err = 0;
		    for (int i = 1; i <= out.size(); i++)
		    {
		    	double p = 1/(1+exp(out[i] * A + B));
		    	pp[i] = p;
		    	if(p!=0)
		    		err -= t * log(p) + (1-t) * log(1-p)
		    	else
		    		err -= t * -200 + (1-t) * -200;
		    }
		    if(err < olderr * (1+1e-7))
		    {
		    	lambda *= 0.1;
		    	break;
		    }

		    lambda *= 10;
		    
		    if(lambda >= 1e6)
		    	break;
		}
		double diff = err -olderr;
		double scale = 0.5 * (err+olderr+1);
		if(diff > -1e-3*scale && diff < 1e-7*scale)
			count++;
		else
			count = 0;
		olderr = err;
		if (count == 3)
			break;
	}

}

float Sigmoid::EvaluateSigmoid(float f)
{
	return 1.0/(1.0+exp(A*f+B));
}