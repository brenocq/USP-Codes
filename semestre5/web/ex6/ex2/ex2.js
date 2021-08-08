// Callback version
function isJoeHappy(happy, callback) {
    setTimeout(() => {
      const happyness = Math.random()
      if (happyness > happy) {
        callback(happyness);
      } else {
        callback(new Error("Joe is sad!"));
      }
    }, 2000);
}

document.getElementById("button-v1").addEventListener('click', ()=>{
	const happy = document.getElementById("input-v1").value
	isJoeHappy(happy, (res)=>{
		if(res instanceof Error == true)
		{
			document.getElementById("result-v1").style.color = "red";
			document.getElementById("result-v1").innerHTML = "No!!! Joe is sad!";
		}
		else
		{
			document.getElementById("result-v1").style.color = "black";
			document.getElementById("result-v1").innerHTML = "Yes! By " + Math.round(res*100)+"%";
		}
	})
})

// Promise version
const isJoeHappyPromise = happy => new Promise((resolve, reject)=> {
	setTimeout(()=>{
      const happyness = Math.random()
      if (happyness > happy) {
		resolve(happyness);
      } else {
		reject();
      }
	}, 2000);
})

document.getElementById("button-v2").addEventListener('click', ()=>{
	const happy = document.getElementById("input-v2").value
	isJoeHappyPromise(happy)
		.then(res => {
			document.getElementById("result-v2").style.color = "black";
			document.getElementById("result-v2").innerHTML = "Yes! By " + Math.round(res*100)+"%";
		})
		.catch(err => {
			document.getElementById("result-v2").style.color = "red";
			document.getElementById("result-v2").innerHTML = "No!!! Joe is sad!";
		})
})

// Async/await version
document.getElementById("button-v3").addEventListener('click', async ()=>{
	const happy = document.getElementById("input-v3").value
	try {
		const res = await isJoeHappyPromise(happy);
		document.getElementById("result-v3").style.color = "black";
		document.getElementById("result-v3").innerHTML = "Yes! By " + Math.round(res*100)+"%";
	} catch(e) {
		document.getElementById("result-v3").style.color = "red";
		document.getElementById("result-v3").innerHTML = "No!!! Joe is sad!";
	}
})
