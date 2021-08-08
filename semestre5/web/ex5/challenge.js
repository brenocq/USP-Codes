let operation = "+";
let lastNumber = 0;
let currNumber = 0;
let currNumberDecimal = 0;

const updateDisplay = ()=>{
	document.getElementById("display").innerHTML = currNumber;
}

//---------- Numbers ----------//
const numberClicked = (number)=>{
	// Confere se numero deverá aparecer antes ou após a vírgula e modifica a variável
	if(currNumberDecimal)
	{
		let power = Math.pow(10,currNumberDecimal);
		currNumber = currNumber+number/power;
		currNumber = Math.round(currNumber * power) / power;
		currNumberDecimal++;
	}
	else
		currNumber = currNumber*10+number;

	// Mostra novo número não for zero para tratar caso em que zero não modifica número
	// se for após a virgula
	if(number!=0)
		updateDisplay();
	else
	{
		document.getElementById("display").innerHTML += "0";
	}
}

for(let i=0;i<10;i++)
	document.getElementById("num"+i).addEventListener('click', ()=>numberClicked(i));

//---------- Point ----------//
const operationPoint = ()=>{
	// Numeros irão aparecer após a vírgula
	if(currNumberDecimal===0)
	{
		currNumberDecimal=1;
		document.getElementById("display").innerHTML +=".";
	}
}
document.getElementById("op-p").addEventListener('click', operationPoint);

//---------- Operations ----------//
const opList = ["op-add", "op-sub", "op-mult", "op-div"];
opList.forEach((op)=>{
	// Para cada tipo de operação, passa o número atual para o ultimo e salva operação
	document.getElementById(op).addEventListener('click', ()=>{
		operation = document.getElementById(op).innerHTML;
		console.log(operation);
		lastNumber = currNumber;
		currNumber = 0;
		currNumberDecimal = 0;
		updateDisplay();
	});
})

//---------- Equal ----------//
document.getElementById("op-eq").addEventListener('click', ()=>{
	// Realiza operação
	switch(operation)
	{
		case "+":
			currNumber = lastNumber+currNumber;
			break;
		case "-":
			currNumber = lastNumber-currNumber;
			break;
		case "*":
			currNumber = lastNumber*currNumber;
			break;
		case "/":
			currNumber = lastNumber/currNumber;
			break;
	}
	currNumberDecimal = 0;
	updateDisplay();
});

//---------- C ----------//
document.getElementById("c").addEventListener('click', ()=>{
	// Limpa toda a entrada
	operation = "+";
	lastNumber = 0;
	currNumber = 0;
	currNumberDecimal = 0;
	updateDisplay();
});

//---------- CE ----------//
document.getElementById("ce").addEventListener('click', ()=>{
	// Limpa ultima entrada
	if(currNumberDecimal)
	{
		currNumberDecimal-=2;
		let power = Math.pow(10,currNumberDecimal);
		currNumber = Math.floor(currNumber * power) / power;
		currNumberDecimal++;
	}
	else
		currNumber = Math.floor(currNumber/10)
	updateDisplay();
});
