public class Main {
	public static void main (String[] args) {
		EntradaTeclado entTec = new EntradaTeclado();
		// Read string
		String str1 = null;
		System.out.print("Your first string: ");
		while(true){
			try{	
				str1 =  entTec.leString();
				break;
			}catch(Exception e){
				System.out.println("Must enter a string. Please try again");
			}
		}
		// Count vogal
		int count = 0;
		for(int i=0;i<str1.length();i++){
			if(str1.charAt(i)=='a' || str1.charAt(i)=='e'|| str1.charAt(i)=='i'|| str1.charAt(i)=='o'|| str1.charAt(i)=='u'){
				count++;
			}
		}
		System.out.println("Qty vogals: "+count);
		// Show upper case
		System.out.println("Upper: "+str1.toUpperCase());
		// Read second string and compare
		String str2 = null;
		System.out.print("Your second string: ");
		while(true){
			try{	
				str2 =  entTec.leString();
				break;
			}catch(Exception e){
				System.out.println("Must enter a string. Please try again");
			}
		}
		System.out.println("Starts with second: "+str1.startsWith(str2));
		System.out.println("Ends with second: "+str1.endsWith(str2));
	}
}
