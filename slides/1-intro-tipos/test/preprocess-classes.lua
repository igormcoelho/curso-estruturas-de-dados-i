-- preprocess-classes.lua
local CLASS_SHORTCUTS = {
  ['{.>}']  = 'flushright',
  ['{.<}']  = 'flushleft',
  ['{.><}'] = 'center',
}

-- Função que processa um único elemento Div/Span
local function process_classes(el)
  local new_classes = {}
  local modified = false
  
  for _, cls in ipairs(el.classes) do
    local mapped = CLASS_SHORTCUTS[cls]
    if mapped then
      table.insert(new_classes, mapped)
      modified = true
      io.stderr:write("DEBUG: mapeando '" .. cls .. "' → '" .. mapped .. "'\n")
    else
      table.insert(new_classes, cls)
    end
  end
  
  if modified then
    el.classes = new_classes
  end
  return el
end

-- Handler para Div
function Div(el)
  return process_classes(el)
end

-- Handler para Span (se precisar inline também)
function Span(el)
  return process_classes(el)
end
