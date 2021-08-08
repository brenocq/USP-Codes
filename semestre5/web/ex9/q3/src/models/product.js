'use strict';

const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const schema = new Schema({
	title: {
		type: String,
		required: true,
		trim: true
	},
	slug: {
		type: String,
		required: true,
		trim: true,
		index: true,
		unique: true
	},
	description: {
		type: String,
		required: true,
		trim: true
	},
	price: {
		type: Number,
		required: true,
		default: 9.99
	},
	tags: [{
		type: String,
		required: true
	}],
	active: {
		type: Boolean,
		required: true,
		default: true
	},
});

module.exports = mongoose.model('Product', schema);
