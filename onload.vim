" Vim Project script configuration

set fdm=marker

"" This configuration should be done only once
if exists('g:did_simple_config')
    finish
endif
let g:did_simple_config = 1

"" Configuration of AppTemplate plugin.
let g:atpl_UsersList['@AUTHORMAIL@']  = 'aantonello@paralaxe.com.br'
let g:atpl_UsersList['@PROJECTNAME@'] = 'Simple Framework'
let g:atpl_UsersList['@PROJECT@']     = 'Simple Framework'
let g:atpl_UsersList['@OWNER@']       = 'Paralaxe Tecnologia'
let g:atpl_UsersList['@VERSION@']     = '2.0'

"" Autocommand group to configure Doxygen properly.
augroup XIOS
    au!
    au BufNewFile,BufRead *.h   setl filetype=objc | setl syntax=objc.doxygen
    au BufNewFile,BufRead *.m   setl syntax=objc.doxygen
augroup END

"" Setting this helps the standard highlight system.
let g:filetype_m = 'objc'

