import java.util.*;

public class MegaSena {
	public static void main (String[] args) {
		int semente = 1024;
		while(true){
			try{
				System.out.print("Digite uma seed: ");
				semente = EntradaTeclado.leInt();
				break;
			}catch(Exception e){
				System.out.println("Please try again.");
			}
		}
		
		Random rand1 = new Random((int)Calendar.getInstance().getTimeInMillis());
		Random rand2 = new Random(semente);
		//rand.setXi(semente);

		//for(int i=0;i<6;i++) {
		//	int num = rand.getIntRand(60)+1;
		//	System.out.println("Num "+i+":"+num);
		//}
		int num1 = 0;
		int num2 = 0;
		int count = 0;
		do{
			num1 = rand1.getIntRand(60)+1;
			num2 = rand2.getIntRand(60)+1;
			System.out.println(num1+" "+num2);
			count++;
		}while(num1!=num2 && count<100);

		System.out.println("Equal at:"+count);
	}
}
