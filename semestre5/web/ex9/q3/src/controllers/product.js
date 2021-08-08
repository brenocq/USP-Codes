'use strict';
const repository = require('../repositories/product');

exports.get = async(req, res, next) => {
	try {
		let data = await repository.get();
		res.status(200).send({products: data});
	} catch(e) {
		res.status(500).send({message: 'Falha ao procurar produtos', data: e});
	}
}

exports.getBySlug = async(req, res, next) => {
	try {
		let data = await repository.getBySlug(req.params.slug);
		res.status(200).send({product: data});
	} catch (e) {
		res.status(500).send({message: 'Falha ao procurar produto', data: e});
	}
}

exports.getById = async(req, res, next) => {
	try {
		let data = await repository.getById(req.params.id)
		res.status(200).send({product: data});
	} catch (e) {
		res.status(500).send({message: 'Falha ao procurar produto', data: e});
	}
}

exports.getByTag = async(req, res, next) => {
	try {
		let data = await repository.getByTag(req.params.tag)
		res.status(200).send({products: data});
	} catch (e) {
		res.status(500).send({message: 'Falha ao procurar produtos', data: e});
	}
}

exports.post = async(req, res, next) => {
	try {
		await repository.create(req.body);
		res.status(201).send({message: 'Cadastrado com sucesso!'});
	} catch (e) {
		res.status(500).send({message: 'Falha ao cadastrar', data: e});
	}
}

exports.put = async(req, res, next) => {
	try {
		await repository.update(req.params.id, req.body);
		res.status(200).send({message: 'Atualizado com sucesso!'});
	} catch (e) {
		res.status(500).send({message: 'Falha ao atualizar', data: e});
	}
}

exports.delete = async(req, res, next) => {
	try {
		await repository.delete(req.params.id);
		res.status(200).send({message: 'Produto removido com sucesso!'});
	} catch (e) {
		res.status(500).send({message: 'Falha ao remover', data: e});
	}
}
