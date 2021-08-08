let app = new Vue({
	el: "#app",
	data: {
		firstName: null,
		lastName: null,
		birth: null,
		city: null,
		sign: null,
	},
	methods: {
		send() {
			if(this.firstName == null || this.lastName == null || this.birth == null || 
				this.city == null || this.sign == null) {
				alert("É necessário preencher todos os dados.");
			}
			else if(!this.isValidate(this.birth)) {
				alert("É necessário inserir uma data válida.");
			}
			else {
				alert("Enviado.");
			}
		},
		isValidate(dateStr) {
			s = dateStr.split('/');
			d = new Date(+s[2], s[1]-1, +s[0]);
			if(Object.prototype.toString.call(d) === "[object Date]") {
				if(!isNaN(d.getTime()) && d.getDate() == s[0] && 
					d.getMonth() == (s[1] - 1)) {
					return true;
				}
			}
		}
	}
})
