//循环体前面定义const double start=clock();然后将其做为第一个参数
bool timer(const double & start,const double& length)
{
	if (((double)clock() - start) / CLK_TCK >= length)
		return false;
	else
		return true;
}



class ctimer
{
	const double start;
	const double length;

public:
	ctimer(const double& len) :start(clock()), length(len){}
	bool blast()
	{
		if ((clock() - start)/CLK_TCK >= length)
			return false;
		else
			return true;
	}
};