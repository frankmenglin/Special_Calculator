#include <iostream>
#include <cmath>
using namespace std;

double American_Call_Option(double S,double K, double sigma, double r, double delta, double t, int step){
    // S=spot,K=strike, sigma=volatility, r=interest rate, delta=dividend rate
    // t=time to expiration, step=number of time step
    double h=t/double(step); //size of time step
    double u=exp((r-delta)*h+sigma*sqrt(h)); //How much price go up in 1 step
    double d=exp((r-delta)*h-sigma*sqrt(h)); //How much price go down in 1 step
    double p=(exp((r-delta)*h)-d)/(u-d); //Risk-Neutral probability of price increasing in a step
    double q=1.0-p; //Risk Neutral probability of price decreasing in a step

    double price_at_expiration [step+1]; //An array that contain possible prices of the underlying at expiration
    double stock_price [step+1];
    double lowest_price=S*pow(d,step);

    for (int i = 0; i <=step; i++) {
    price_at_expiration[i]=lowest_price*pow(u,i)/pow(d,i);
    stock_price[i]=lowest_price*pow(u,i)/pow(d,i);
    }//All possible prices of underlying at expiration

    double call_price [step+1]; //Call option price array
    for (int i = 0; i <=step; i++) {
    call_price[i]=fmax(0.0, price_at_expiration[i]-K);
    }//Initialized the array by containing all possible call option prices at expiration

    for (int j=1; j<=step ;j++){
            for (int i=0; i<=step-j;i++){
                stock_price[i]=stock_price[i]/d;
                call_price[i]=fmax(stock_price[i]-K,(call_price[i]*q+call_price[i+1]*p)*exp(-r*h));
            }
    }
    return call_price[0];
}

int main()
{
    cout << American_Call_Option(100,105,0.25,0.015, 0.05, 0.5, 500);
    //S,K,sigma,r,delta,T-t,total time steps
	return 0;
}
