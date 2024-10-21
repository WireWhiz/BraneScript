// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterBranescriptParser",
    products: [
        .library(name: "TreeSitterBranescriptParser", targets: ["TreeSitterBranescriptParser"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterBranescriptParser",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterBranescriptParserTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterBranescriptParser",
            ],
            path: "bindings/swift/TreeSitterBranescriptParserTests"
        )
    ],
    cLanguageStandard: .c11
)
