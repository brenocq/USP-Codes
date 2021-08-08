let allItems = ["Mulher Maravilha", "Brainiac", "Aquaman", "Ravena", "Batman", "Superman", "Mulher Gavião", "Flash", "Lanterna Verde", "Shazam"];

let app = new Vue({
	el: "#app",
	data: {
		searchText: "",
		filtered: allItems
	},
	watch: {
		searchText(newValue) {
			this.filtered = allItems.filter(i=>(i.toLowerCase().includes(newValue.toLowerCase())));
		}
	}
})
