--- div-shortcuts.lua - Useful shortcuts for fonts and alignment in Pandoc
---
--- Copyright: © 2026 Igor Machado Coelho
--- License: MIT - see LICENSE for details
---
-- Ensure pandoc supports Lua!!
PANDOC_VERSION:must_be_at_least '2.17'

-- div-shortcuts.lua

local CLASS_SHORTCUTS = {
  ['<']    = 'flushleft',
  ['>']    = 'flushright',
  ['<>']   = 'center', -- originally, this was justify, but community thinks it's center!
  ['><']   = 'center', -- originally, this was center! So now BOTH are center!!
  ['|']    = 'column',
  ['||']   = 'columns',
  ['-']    = 'small',
  ['--']   = 'xsmall',
  ['---']  = 'xxsmall',
  ['----'] = 'tiny',
  ['+']    = 'large',
  ['++']   = 'xlarge',
  ['+++']  = 'xxlarge',
  ['++++'] = 'huge',
--  ['xxxx'] = 'yyyyy', -- JUST ADD ANOTHER ONE TO THIS LIST IF YOU WANT!!
}

-- IMPORTANT: some classes have default attributes.
-- Example: column is very likely to setup with width=X%
--   but 'width' is hard to write and hard to remember!
-- So we assume, for these classes, that first independent 
--   parameter is the default one!
--  |{60%} is equivalent to {.column width=60%}

local CLASS_DEFAULT_ATTR = {
  ['column']  = 'width',
--  ['xxxx'] = 'yyyyy', -- JUST ADD ANOTHER ONE TO THIS LIST IF YOU WANT!!
}

local function parse_attrs(attrs_str, mapped_class)
  local attrs = {}
  local has_kv = attrs_str:find('=')

  if has_kv then
    for key, val in attrs_str:gmatch('([%w_%-]+)=([^;]+)') do
      attrs[key] = val:match('^%s*(.-)%s*$')
    end
  else
    local default_key = CLASS_DEFAULT_ATTR[mapped_class]
    if default_key and attrs_str ~= '' then
      attrs[default_key] = attrs_str
    end
  end

  return attrs
end

local function apply_shortcuts(el)
  local new_classes = {}
  for _, cls in ipairs(el.classes) do
    local symbol, attrs_str = cls:match('^(.-)%{(.*)%}$')
    if not symbol then
      symbol = cls
    end
    local mapped = CLASS_SHORTCUTS[symbol]
    if mapped then
      table.insert(new_classes, mapped)
      if attrs_str then
        local attrs = parse_attrs(attrs_str, mapped)
        for k, v in pairs(attrs) do
          el.attributes[k] = v
        end
      end
    else
      table.insert(new_classes, cls)
    end
  end
  el.classes = new_classes
  return el
end

function Div(el)
  return apply_shortcuts(el)
end

function Span(el)
  return apply_shortcuts(el)
end
