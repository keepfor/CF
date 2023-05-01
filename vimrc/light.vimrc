nnoremap <c-a> ggvG$
nnoremap <s-j> :e input.txt
nnoremap <s-k> :!make
nnoremap <s-l> :q!
nnoremap <s-r> :!make re
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
nnoremap <F4> :!bash /home/jackcai/scripts/start_ftu.sh
nnoremap <F3> :e ~/j/ftu_log_folder
inoremap jk <esc>
inoremap kj <esc>
nnoremap ; :

set visualbell
set t_ti= t_te= t_TI= t_TE=
set timeoutlen=10
set splitbelow
set expandtab
set nocompatible 
set number 
set nobackup
set autochdir
set clipboard^=unnamed,unnamedplus 
set mouse=a
set smartindent autoindent cindent
set backspace=indent,eol,start
set shiftwidth=2 softtabstop=2 tabstop=2
set backupcopy=yes 
set ignorecase smartcase 
set incsearch hlsearch 

filetype plugin indent on   
command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')
