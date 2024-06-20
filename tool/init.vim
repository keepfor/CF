colorscheme habamax 

inoremap jk <esc>
inoremap kj <esc>

nnoremap ; :
nnoremap * *``
nnoremap <s-q> :q!
nnoremap <c-a> gg^vG$
nnoremap <c-d> *``cgn
nnoremap <c-c> :noh<cr>

nnoremap <c-h> <c-w>h
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-l> <c-w>l

nnoremap <c-n> :tabnext<cr>
nnoremap <c-p> :tabprevious<cr>
nnoremap <c-t> :tabedit

set shiftwidth=2 softtabstop=2 tabstop=2
set visualbell nobackup
set t_ti= t_te= t_TI= t_TE=
set timeoutlen=50 mouse=a
set expandtab nocompatible 
set backupcopy=auto
set autochdir autoread
set clipboard^=unnamed,unnamedplus 
set smartindent autoindent cindent
set backspace=indent,eol,start
set ignorecase smartcase 
set incsearch hlsearch nu

command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')

inoremap { {}<left>
inoremap <expr> <CR> search('{\%#}', 'n') ? "\<CR>\<CR>\<Up>\<C-f>" : "\<CR>"
inoremap <expr> } strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}"

call plug#begin()
Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"
inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"
function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction
