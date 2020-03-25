public class Main{
	public static void main(String[] args){
		Televisao tel = new Televisao();
		Controle con = new Controle(tel);

		System.out.println("Aumentar volume");
		for(int i=0;i<10;i++){
			con.aumentarVolume();
			System.out.println("Volume: "+tel.getVolume());
		}

		System.out.println("Diminuir volume");
		for(int i=0;i<10;i++){
			con.diminuirVolume();
			System.out.println("Volume: "+tel.getVolume());
		}

		System.out.println("Aumentar canal");
		for(int i=0;i<20;i++){
			con.diminuirCanal();
			System.out.println("Canal: "+tel.getCanal());
		}

		System.out.println("Definir canal");
		for(int i=20;i>=0;i--){
			con.definirCanal(i);
			System.out.println("Canal: "+tel.getCanal());
		}
	}
}	
