public class Random {
	public Random(int k){
		xi = k;
	}

	// Generation parameteres
	private long p = 3648L;
	private long m = 7094L;
	private long a = 35039L;

	public long xi = 1023;// Seed

	public double getRand() {
		xi = (a+m*xi)%p;
		return (double)xi/p;
	}
	
	public int getIntRand(int max) {
		double d = getRand()*max;
		return (int)d;
	}

	public void setXi(int _xi){
		xi = _xi;
	}
}
