import XCTest
import SwiftTreeSitter
import TreeSitterBranescriptParser

final class TreeSitterBranescriptParserTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_branescript_parser())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading BranescriptParser grammar")
    }
}
