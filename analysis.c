#include <stdio.h>

double function(double);
double lagrangeInterpolation(int, double);
double piecewiseInterpolation(int, double);
double newtonInterpolation(int, double);
// int factorial(int);
// int times(int, int);

int main(int argc, char const *argv[])
{
	// while(1)
	// {
	// 	double x;
	// 	int n;
	// 	scanf("%d%lf", &n, &x);
	// 	printf("ExactValue:%.8lf  LagrangeInterpolation:%.8lf  Deviation:%.8lf\n", 
	// 		function(x), lagrangeInterpolation(n, x), function(x) - lagrangeInterpolation(n, x));
	// 	printf("ExactValue:%.8lf  PiecewiseInterpolation:%.8lf  Deviation:%.8lf\n", 
	// 		function(x), piecewiseInterpolation(n, x), function(x) - piecewiseInterpolation(n, x));

	// }
	int n = 0;
	double x = 0;
	scanf("%d %lf", &n, &x);
	printf("%lf\n", newtonInterpolation(n, x));

	// printf("%d %d", factorial(5), times(3, 3));
	return 0;
}

double function(double x)
{
	return 1.0/(1.0 + x * x);
}

double lagrangeInterpolation(int n, double x)
{
	int count = n + 1;
	double xArray[100];
	double yArray[100];
	double mul = 1.0, sum = 0.0;
	for(int i = 0; i < count; i++)	//input x, y
	{
		xArray[i] = (-5.0 + i * 10.0 / n) * 1.0;
		yArray[i] = function(xArray[i]);
	}

	for(int j = 0; j < count; j++)  //count
	{
		for(int k = 0; k < count; k++)
		{
			if(j != k)
			{
				mul *= 1.0 * (x - xArray[k]) / (xArray[j] - xArray[k]);	
			}
		}
		sum += mul*yArray[j];
		mul = 1.0;
	}
	// int temp = sum * 10000000;	//cf
	// if(temp % 10 > 4)
	// 	sum += 0.000001;
	return sum;
}

double piecewiseInterpolation(int n, double x)
{
	int count = n + 1;
	int left = 0, right = n, mid = n / 2;
	double xArray[100];
	double yArray[100];
	double sum = 0.0;
	for(int i = 0; i < count; i++)	//input x, y
	{
		xArray[i] = (-5.0 + i * 10.0 / n) * 1.0;
		yArray[i] = function(xArray[i]);
	}

	while(left != mid)	//binary search
	{
		if(x < xArray[left] || x > xArray[right])
		{
			printf("wrong number");
		}

		if(x <= xArray[mid])
		{
			right = mid;
			mid = (left + right) / 2;
		}else{
			left = mid;
			mid = (left + right) / 2;
		}
	}
	sum = yArray[mid]
		  + (yArray[mid + 1] - yArray[mid])
		  / (xArray[mid + 1] - xArray[mid])
	      * (x - xArray[mid]);
	return sum;
}

double newtonInterpolation(int n, double x)
{
	double xArray[10];
	double yArray[10];
	double fun[100][100];
	double sum = 0.0;

	for(int i = 0; i < n; i++)	//input x, y
	{
		scanf("%lf%lf", &xArray[i], &yArray[i]);
		fun[i][i] = yArray[i];
	}

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < n - i; j++)
        {
            fun[j][j + i] = (fun[j + 1][j + i] - fun[j][j + i - 1]) / (xArray[j + i] - xArray[j]);
        }
    }

    sum = yArray[0];
    for(int i = 1; i <= n; i++)
    {
        double temp = 1.0;
        for(int j = 0; j < i; j++){
            temp = temp * (x - xArray[j]);
        }
        sum = sum + temp * fun[0][i];
    }
    
    return sum;
}

// int factorial(int n)
// {
// 	if(n == 0)
// 		return 1;
// 	return n * factorial(n - 1);
// }

// int times(int x, int n)
// {
// 	if(n == 0)
// 		return 1;
// 	else
// 		return x * times(x, n - 1);
// }