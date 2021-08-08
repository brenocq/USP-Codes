//---------- Questão 4 ----------//
function isLetter(a)
{
	return (a>="a" && a<="z") || (a>="A" && a<="Z") || a=="-"
}

const highlightText = ()=>{
	// Vamos percorrer o innerHTML adicionando <span style="color:xxxx;"></span> em palavras que devem ser coloridas, ignorando
	// caracteres que não são letras
	// O código a seguir funciona bem para o exemplo, mas pode apresentar falhas se aplicado a um parágrafo genérico com várias tags filho
	
	let pInner = document.querySelectorAll("p")[0].innerHTML.split("<a")[0]// innerHTML without <a> tag
	let pInnerA = "<a"+document.querySelectorAll("p")[0].innerHTML.split("<a")[1]// <a> tag
	let finalInner = ""// innerHTML final com palavras estilizadas
	let currWord = ""// Conjunto de letras em sequência no vertor pInner
	for(let i=0;i<pInner.length;i++)
	{
		if(isLetter(pInner[i]))
			currWord+=pInner[i]
		else
		{
			// Se o próximo caractere não for uma letra, confere se precisa mudar a cor da paralavra e adiciona
			// (currWord+novo caractere) ao finalInner
			// a)
			if(currWord.length>=8)
				finalInner+="<span style=\"background-color:pink;\">"+currWord+"</span>"+pInner[i]
			// b)
			else if(currWord.length==6)
				finalInner+="<span style=\"background-color:#99F;\">"+currWord+"</span>"+pInner[i]// Utilizando #99F para ficar mais legível
			// c)
			else if(currWord.length==4 || currWord.length==5)
				finalInner+="<span style=\"background-color:#A5A;\">"+currWord+"</span>"+pInner[i]// Utilizando #A5A para ficar mais legível
			else
				finalInner+=currWord+pInner[i]
			currWord = ""
		}
	}

	// Altera para o innerHTML estilizado mais a <a> tag
	document.querySelectorAll("p")[0].innerHTML = finalInner+pInnerA
}

document.getElementById("highlight").addEventListener('click', highlightText)
