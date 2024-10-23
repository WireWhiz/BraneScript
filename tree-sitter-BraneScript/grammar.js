/**
 * @file Parser for BraneScript text files
 * @author WireWhiz
 * @license Apache 2.0
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "BraneScript",

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => repeat($._expression),
    _expression: $ => choice(
        $._binary_expression,
        prec(0, $.number),
    ),
    _binary_expression: $ => prec(1, choice(
        $.add,
        $.sub,
        $.mul,
        $.div
    )),
    number: $ => /\d+/,
    add: $ => prec.left(1, seq(
        $._expression,
        "+",
        $._expression
    )),
    sub: $ => prec.left(1, seq(
        $._expression,
        "-",
        $._expression
    )),
    mul: $ => prec.left(2, seq(
        $._expression,
        "*",
        $._expression
    )),
    div: $ => prec.left(2, seq(
        $._expression,
        "/",
        $._expression
    )),
  }
});
