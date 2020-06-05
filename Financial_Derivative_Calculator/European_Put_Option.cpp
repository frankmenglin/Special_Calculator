#include <iostream>
#include <cmath>
using namespace std;

double European_Put_Option(double S,double K, double sigma, double r, double delta, double t, int step){
    // S=spot,K=strike, sigma=volatility, r=interest rate, delta=dividend rate
    // t=time to expiration, step=number of time step
    double h=t/double(step); //size of time step
    double u=exp((r-delta)*h+sigma*sqrt(h)); //How much price go up in 1 step
    double d=exp((r-delta)*h-sigma*sqrt(h)); //How much price go down in 1 step
    double p=(exp((r-delta)*h)-d)/(u-d); //Risk-Neutral probability of price increasing in a step
    double q=1.0-p; //Risk Neutral probability of price decreasing in a step

    double price_at_expiration [step+1]; //An array that contain possible prices of the underlying at expiration
    double lowest_price=S*pow(d,step);

    for (int i = 0; i <=step; i++) {
    price_at_expiration[i]=lowest_price*pow(u,i)/pow(d,i);
    }//All possible prices of underlying at expiration

    double put_price [step+1]; //Put option price array
    for (int i = 0; i <=step; i++) {
    put_price[i]=fmax(0.0, K-price_at_expiration[i]);
    }//Initialized the array by containing all possible put option prices at expiration

    for (int j=1; j<=step ;j++){
            for (int i=0; i<=step-j;i++){
                put_price[i]=(put_price[i]*q+put_price[i+1]*p)*exp(-r*h);
            }
    }
    return put_price[0];
}
double normalCDF(double x) // N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}
double European_Put_Option_continuous(double S,double K, double sigma, double r, double delta, double t){
    double d1;
    double d2;
    d1=(log(S/K)+(r-delta+0.5*pow(sigma,2))*t)/(sigma*pow(t,0.5));
    d2=(log(S/K)+(r-delta-0.5*pow(sigma,2))*t)/(sigma*pow(t,0.5));
    return -S*normalCDF(-d1)*exp(-delta*t)+K*normalCDF(-d2)*exp(-r*t);
}//Pricing using continuous model
int main()
{
    cout << European_Put_Option(100,105,0.25,0.015, 0.0, 0.5, 2000)<<endl;
    //S,K,sigma,r,delta,T-t,total time steps
    cout << European_Put_Option_continuous(100,105,0.25,0.015, 0.0, 0.5);
	return 0;
}
