-- debug-ast.lua
function Pandoc(doc)
  io.stderr:write("=== AST RECEBIDO ===\n")
  io.stderr:write(pandoc.write(doc, 'native'))
  io.stderr:write("\n=== FIM AST ===\n")
  return doc
end

