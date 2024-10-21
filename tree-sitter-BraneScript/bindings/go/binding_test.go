package tree_sitter_branescript_parser_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_branescript_parser "github.com/wirewhiz/branescript/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_branescript_parser.Language())
	if language == nil {
		t.Errorf("Error loading BranescriptParser grammar")
	}
}
