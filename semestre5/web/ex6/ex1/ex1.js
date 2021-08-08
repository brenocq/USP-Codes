const changeColor = () => {
	let color = document.getElementById("color-input").value;
	let usePromises = false

	// Request color
	fetch(`https://reqres.in/api/unknown/${color}`)
		.then((response) => {
			return response.json();
		})
		.then((data) => {
			let colorHex = data.data.color;
			let colorName = data.data.name;
			// Update info about color
			document.getElementById("color-info").innerHTML = colorHex+"<br>"+colorName;
			// Update square color
			document.getElementById("color-display").style.backgroundColor = colorHex;
		}).catch(e=>{
			// Handle errors
		});
}

// Version with async/await (ex3)
const changeColorAwait = async () => {
	let color = document.getElementById("color-input").value;

	// Request color
	let response = await fetch(`https://reqres.in/api/unknown/${color}`);
	let data = await response.json();
	try {
		let colorHex = data.data.color;
		let colorName = data.data.name;
		// Update info about color
		document.getElementById("color-info").innerHTML = colorHex+"<br>"+colorName;
		// Update square color
		document.getElementById("color-display").style.backgroundColor = colorHex;
	} catch(e) {
		// Handle errors
	}
}

document.getElementById("change-color-button").addEventListener('click', changeColorAwait);
