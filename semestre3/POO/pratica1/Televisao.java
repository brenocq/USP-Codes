public class Televisao{
	private int volume = 50;
	private int canal = 1;	

	public void aumentarVolume(){
		if(volume<100)
			volume++;
	}

	public void diminuirVolume(){
		if(volume>0)
			volume--;
	}

	public void aumentarCanal(){
		if(canal<10)
			canal++;
	}

	public void diminuirCanal(){
		if(canal>0)
			canal--;
	}

	public void definirCanal(int c){
		if(c>0 && c<10)	
			canal = c;
	}

	public int getCanal(){
		return canal;
	}

	public int getVolume(){
		return volume;
	}
}
