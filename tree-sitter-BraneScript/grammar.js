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
    source_file: $ => "hello"
  }
});
