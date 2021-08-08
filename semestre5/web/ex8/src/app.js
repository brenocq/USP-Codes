const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const router = express.Router();

app.use(bodyParser.json());
app.use(express.static('public'));
app.use(bodyParser.urlencoded({extended:false}));

let db = {};

const read = router.get('/:key', (req, res, next) => {
	const key = req.params.key;
	let output;
	if(db[key] == undefined)
		output = "";
	else
		output = JSON.parse(db[key]);

	res.status(200).send(output);
});

const write = router.put('/:key', (req, res, next) => {
	const key = req.params.key;
	console.log(req.body)
	// Converte de objeto para string ao armazenar
	db[key] = JSON.stringify(req.body);
	res.status(200).send({message: "Added to database. db["+key+"]="+JSON.stringify(db[key])});
});

const del = router.delete('/:key', (req, res, next) => {
	const key = req.params.key;
	delete db[key];
	res.status(200).send({message: "Deleted from database"});
});


app.use('/store', read);
app.use('/store', write);
app.use('/store', del);

module.exports = app;
