public class Controle{
	private Televisao televisao = null;

	public Controle(Televisao tel){
		televisao = tel;
	}

	public void aumentarVolume(){
		televisao.aumentarVolume();
	}

	public void diminuirVolume(){
		televisao.diminuirVolume();
	}

	public void aumentarCanal(){
		televisao.aumentarCanal();
	}

	public void diminuirCanal(){
		televisao.diminuirCanal();
	}
	
	public void definirCanal(int canal){
		televisao.definirCanal(canal);
	}

}
