//---------- Ex1 ----------//
function makeMadTalk() {
	let noun = document.getElementById("noun").value
	let adjective = document.getElementById("adjective").value
	let person = document.getElementById("person").value

	let sentence = `${person} was walking and fell on the ${adjective} ${noun}`
	document.getElementById("story").innerHTML = sentence;
}

document.getElementById("lib-button").addEventListener('click', makeMadTalk)
