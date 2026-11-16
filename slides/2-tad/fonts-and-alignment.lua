--- fonts-and-alignment.lua - Sets the fonts and alignment in LaTeX documents
---
--- Copyright: © 2021-2022 Nandakumar Chandrasekhar
--- License: MIT - see LICENSE for details
---
-- Makes sure users know if their pandoc version is too old for this filter.
PANDOC_VERSION:must_be_at_least '2.17'

-- For the tables below the first variable in the LaTeX code for an inline
-- element or Span and the second is far a block element or Div.

-- LaTeX font types
LATEX_FONT_TYPES = {
  bold = { 'textbf', 'bfseries' },
  emphasis =  { 'emph', 'em' },
  italic = { 'textit', 'itshape' },
  lower = { 'lowercase', nil },
  medium = { 'textmd', 'mdseries' },
  monospace = { 'texttt', 'ttfamily' },
  normalfont = { 'textnormal', 'normalfont' },
  sans = { 'textsf', 'sffamily' },
  serif = { 'textrm', 'rmfamily' },
  slanted = { 'textsl', 'slshape' },
  smallcaps = { 'textsc', 'scshape' },
  upper = { 'uppercase', nil },
  upright = { 'textup', 'upshape'},
  bf = { 'textbf', 'bfseries' },
  em =  { 'emph', 'em' },
  it = { 'textit', 'itshape' },
  md = { 'textmd',  'mdseries' },
  tt = { 'texttt', 'ttfamily' },
  nf = { 'textnormal', 'normalfont' },
  sf = { 'textsf', 'sffamily' },
  rm = { 'textrm', 'rmfamily' },
  sc = { 'textsc', 'scshape' },
  sl = { 'textsl', 'slshape' },
  up = { 'textup', 'upshape'},
}

-- LaTeX font sizes
LATEX_FONT_SIZES = {
  tiny = { 'tiny', 'tiny' },
  xxsmall = { 'scriptsize', 'scriptsize'},
  xsmall = { 'footnotesize', 'footnotesize' },
  small = { 'small', 'small' },
  normal = { 'normalsize', 'normalsize' },
  large = { 'large', 'large' },
  xlarge = { 'Large', 'Large' },
  xxlarge = { 'LARGE', 'LARGE' },
  huge = { 'huge', 'huge' },
}

-- LaTeX text alignments
LATEX_TEXT_ALIGNMENTS = {
  center = { nil, 'center' },
  flushright = { nil, 'flushright' },
  flushleft = { nil, 'flushleft' },
  centering = { nil, 'centering' },
  raggedleft = { nil, 'raggedleft' },
  raggedright = { nil, 'raggedright' },
}

-- LaTeX ulem styles
LATEX_ULEM_STYLES = {
  dashuline = {'dashuline', nil},
  dotuline = {'dotuline', nil},
  uline = {'uline', nil},
  uuline = {'uuline', nil},
  uwave = {'uwave', nil},
  sout = {'sout', nil},
  xout = {'xout', nil},
  dau = {'dashuline', nil},
  dou = {'dotuline', nil},
  so = {'sout', nil},
  u = {'uline', nil},
  uu = {'uuline', nil},
  uw = {'uwave', nil},
  xo = {'xout', nil},
}

-- Pandoc code to write raw inline and raw block elements
RAW_CODE_FUNCTION = {
  Span = pandoc.RawInline,
  Div = pandoc.RawBlock
}

-- Save some typing and check that we have got the pandoc libraries
local p = assert(pandoc, "Cannot find the pandoc library")
if not ('table' == type(p)) then
  error("Expected variable pandoc to be a table")
end
local utils = assert(pandoc.utils, "Cannot find the pandoc.utils library")
local List = assert(pandoc.List, "Cannot find the pandoc.List class")

-- Convert the given value to a string
local function stringify(val, accept_bool)
  -- First try converting to a string
  local status, retval = pcall(utils.stringify, val)
  if status and retval then
    return retval
  end
  local val_type = utils.type(val)
  if ((val_type == "string" ) or (val_type == "number") or
        (accept_bool and (val_type == "boolean"))) then
    return tostring(val)
  else
    return error("Cannot convert to string " .. val_type)
  end
end

-- Convert appropriate values in meta or env to boolean
local get_bool_val = {
  ["true"]  = true,  -- string to bool
  ["false"] = false,
  yes = true,
  no  = false
}

-- Convert the given value to a boolean
local function boolify (val)
  local str = stringify(val, true):lower() -- case insensitive
  return get_bool_val[str]
end

-- Table to hold the constructed LaTeX commands
-- categorized by tag and then by class name
local latex_cmd_for_tags = {
  Span = {},
  Div = {}
}

-- Construct the LaTeX code based on type of element
local function construct_latex_cmd(class, span_code, div_code, span_end_code)
  -- Construct codes for span
  if span_code then
    -- Decide on the format of the LaTeX code for spans based on this variable
    if not span_end_code then
      latex_cmd_for_tags.Span[class] = {'\\' .. span_code .. ' ', nil}
    else
      latex_cmd_for_tags.Span[class] = {'\\' .. span_code .. '{', '}'}
    end
  end
  -- Consruct codes for div
  if div_code then
    latex_cmd_for_tags.Div[class] = {
      '\\begin{' .. div_code .. '}', '\\end{' .. div_code .. '}'
    }
  end
end

-- Create the LaTeX codes for elements by extracting them from the given table
local function create_latex_codes(styles_list, span_end_code)
  -- This variable helps us construct the correct LaTeX start and end code
  span_end_code = (span_end_code == nil and false) or span_end_code
  for class, latex_codes in pairs(styles_list) do
    -- Check that the table latex_codes is not empty
    if next(latex_codes) then
      local span_code = latex_codes[1]
      local div_code = latex_codes[2]
      construct_latex_cmd(class, span_code, div_code, span_end_code)
    end
  end
end

-- Create the LaTeX commands for font types, font sizes and layouts
create_latex_codes(LATEX_FONT_TYPES, true)
create_latex_codes(LATEX_FONT_SIZES)
create_latex_codes(LATEX_TEXT_ALIGNMENTS)

-- This function takes an element object and returns it with
-- the LaTeX codes applied based on the classes attached to the element
local function handler (elem)
  local tag = elem.tag

  -- We can use the code for Spans for styling Links as well
  if tag == "Link" then
    tag = "Span"
  end

  local raw = RAW_CODE_FUNCTION[tag]
  local code_for_class = latex_cmd_for_tags[tag]
  local classes = elem.classes

  -- Iterating over the classes in the element is more efficient.
  -- Looping backwards so that the LaTeX commands come in the
  -- same order the classes were specified in the source document.
  for i=#classes, 1, -1  do
    if code_for_class[classes[i]] then
      local code = code_for_class[classes[i]]
      local begin_code = code[1] -- LaTeX code placed in front
      local end_code = code[2] -- LaTeX code placed at the end

      -- Add LaTeX code at the beginning
      table.insert(elem.content, 1, raw('latex', begin_code))
      if end_code then
        -- Add LaTeX code at the end
        table.insert(elem.content, raw('latex', end_code))
      end
    end
  end
  return elem
end

-- Let the user request the ulem styles through a metadata field
local function Meta(meta)
  -- Check if we have a meta value specifying ulem styles
  local uline_styles_metavar = meta.ulem_styles

  -- If the metadata is not specified set it to false
  if uline_styles_metavar == nil then
    uline_styles_metavar = false
  end

  uline_styles_metavar = boolify(uline_styles_metavar)

  -- Validate the result: if it was a boolean or an appropriate string
  -- it is now a boolean. If not it is now a nil, and probably a mistake.
  if uline_styles_metavar == nil then
    error("Expected meta.ulem_styles should be 'true', 'false' or unset")
  end

  -- If the user wants ulem styles make sure we have a list of header-includes
  if uline_styles_metavar then
    -- Get header-includes if any
    local includes = meta['header-includes']
    -- Default to a List
    includes = includes or List({ })
    -- If not a List make it one!
    if 'List' ~= utils.type(includes) then
      includes = List({ includes })
    end
    -- Add the ulem usepackage LaTeX statement
    includes:insert(p.RawBlock('latex', "\\usepackage[normalem]{ulem}"))
    -- Make sure Pandoc gets our changes
    meta['header-includes'] = includes

    -- Create the ulem LaTeX codes
    create_latex_codes(LATEX_ULEM_STYLES, true)

    -- Make sure Pandoc gets our changes
    return meta
  end
  -- No request, do nothing
  return nil
end

-- Call handler for each Div, Link and Span element
return {
  { Meta = Meta},
  { Div = handler,
    Link = handler,
    Span = handler
  }
}
