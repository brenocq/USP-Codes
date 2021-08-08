'use strict';
const repository = require('../repositories/customer');

exports.post = async(req, res, next) => {
	try {
		await repository.create(req.body);
		res.status(201).send({message: 'Cadastrado com sucesso!'});
	} catch (e) {
		res.status(500).send({message: 'Falha ao cadastrar', data: e});
	}
}

exports.get = async(req, res, next) => {
	try {
		let data = await repository.get();
		res.status(200).send({customers: data});
	} catch(e) {
		res.status(500).send({message: 'Falha ao procurar usuarios', data: e});
	}
}
