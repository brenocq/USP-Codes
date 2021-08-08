//---------- Questão 1 ----------//
{
	let homeLink = document.createElement("a")
	homeLink.href = "index.html"// Também é possível utilizar #, mas foi descontinuado e talvez não funcione no futuro
	homeLink.textContent = "Home"
	// Adicionando novo elemento ao final do parágrafo
	document.querySelector("p").textContent+=" "// Adicionando espaçamento entre . e Home
	document.querySelector("p").appendChild(homeLink)
}

//---------- Questão 2 ----------//
{
	// Utilizando innerHTML ao invés de textContent para manter o elemento a
	let pText = document.querySelector("p").innerHTML

	// Vale ressaltar que sentenças são mais complexos que a divisão apresentada abaixo. Por exemplo, seria necessário 
	// analisar o contexto para decidir o significado de cada vírgula para determinar se deve existir ou não quebra de 
	// linha. Como simplificação, não foi foram tratados os casos mais específicos
	// Realizando quebra de linha diferentes tipos separadores de sentença
	let toReplace = [". ", ".\" ", "! ", "; ", ";\" "]
	for(let r of toReplace)
		pText = pText.replaceAll(r, r+"<br>")

	// Atualizando innerHTML
	document.querySelector("p").innerHTML = pText
}

//---------- Questão 3 ----------//
{
	let text = document.querySelector("p").textContent
	let words = text.split(" ")

	// Conta palavras válidas
	let counter = 0
	for(let word of words)
		if(word.length>0)
			counter++

	// Cria elemento para mostrar contador
	let counterElement = document.createElement("p")
	counterElement.textContent = counter

	// Adiciona elemento antes do heading
	let heading = document.querySelector("h1")
	heading.parentElement.insertBefore(counterElement, heading)
}

//---------- Questão 4 ----------//
function isLetter(a)
{
	return (a>="a" && a<="z") || (a>="A" && a<="Z") || a=="-"
}

{
	// Vamos percorrer o innerHTML adicionando <span style="color:xxxx;"></span> em palavras que devem ser coloridas, ignorando
	// caracteres que não são letras
	// O código a seguir funciona bem para o exemplo, mas pode apresentar falhas se aplicado a um parágrafo genérico com várias tags filho
	
	let pInner = document.querySelectorAll("p")[1].innerHTML.split("<a")[0]// innerHTML without <a> tag
	let pInnerA = "<a"+document.querySelectorAll("p")[1].innerHTML.split("<a")[1]// <a> tag
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
	document.querySelectorAll("p")[1].innerHTML = finalInner+pInnerA
}
