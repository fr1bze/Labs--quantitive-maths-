double* b = new double[N-1];
	double* alpha = new double[N-1];
	double* beta = new double[N-1];

	int i;
	
	alpha[0] = - TDM[2][0]/TDM[1][0];
	beta[0] = F[0]/TDM[1][0];

	for (i=1; i<N-1; i++)
	{
		alpha[i] = -TDM[2][i]/(TDM[1][i] + TDM[0][i]*alpha[i-1]);
		beta[i] = (F[i]-TDM[0][i]*beta[i-1])/(TDM[1][i] + TDM[0][i]*alpha[i-1]);
	}
	b[N-1] = (F[N-1]-TDM[0][N-1]*beta[N-2])/(TDM[1][N-1] + TDM[0][N-1]*alpha[N-2]);

	for (i=N-2; i>-1; i--)
	{
		 b[i] = b[i+1] * alpha[i] + beta[i];
	}
    return b;