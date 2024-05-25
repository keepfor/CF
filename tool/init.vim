inoremap { {}<left>
inoremap <expr> <CR> search('{\%#}', 'n') ? "\<CR>\<CR>\<Up>\<C-f>" : "\<CR>"
inoremap <expr> } strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}"

nnoremap ; :

inoremap jk <esc>
inoremap kj <esc>

nnoremap <c-a> ggvG$
nnoremap <c-h> <c-w>h
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-l> <c-w>l
nnoremap <right> :tabnext<cr>
nnoremap <left> :tabprevious<cr>
nnoremap <s-t> :tabedit

nnoremap <s-q> :q!
nnoremap <s-k> :!time make<cr>
nnoremap <s-j> :!cat > in<cr>

set shiftwidth=2 softtabstop=2 tabstop=2
set visualbell nobackup
set t_ti= t_te= t_TI= t_TE=
set timeoutlen=50 mouse=a
set expandtab nocompatible 
set backupcopy=yes
set autochdir autoread
set clipboard^=unnamed,unnamedplus 
set smartindent autoindent cindent
set backspace=indent,eol,start
set ignorecase smartcase 
set incsearch hlsearch nu

command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')

call plug#begin()
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'mg979/vim-visual-multi', {'branch': 'master'}
call plug#end()

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

inoremap <silent><expr> <down>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<down>" :
      \ coc#refresh()
inoremap <expr><up> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"
inoremap <silent><expr> <cr> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<cr>\<c-r>=coc#on_enter()\<cr>"

colorscheme zellner 
