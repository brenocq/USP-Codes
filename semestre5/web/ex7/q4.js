let app = new Vue({
	el: "#app",

	data: {
		taskInput: "",
		todo: ["Limpar casa", "Alimentar gato", "Preparar comida"],
		done: ["Beber agua", "Acordar"]
	},
	methods: {
		add(){
			// Check already added
			let add = true;
			this.todo.concat(this.done).forEach(t=>{
				if(t==this.taskInput) {
					alert("Esta tarefa já foi adicionada.");
					add = false;
				}
			})
			// Add new task
			if(add) this.todo.push(this.taskInput);
		},
		taskDone(task){
			this.todo = this.todo.filter(t=>t!=task);
			this.done.push(task);
		},
		taskTodo(task){
			this.done = this.done.filter(t=>t!=task);
			this.todo.push(task);
		},
		remove(task){
			this.todo = this.todo.filter(t=>t!=task);
			this.done = this.done.filter(t=>t!=task);
		}
	},
	mounted: function () {
        this.$nextTick(function () {
            window.setInterval(() => {
				if(this.todo.length>0) {
					let r = Math.floor(Math.random()*this.todo.length);
					this.taskDone(this.todo[r]);
				}
            },60000);
        })
    }
})
