import os

version = open('../driver/verbuild.h').read().rstrip().split()[-1]
verstring = '"2.1.%s"' % version

OLD = 'VidUSB2.rc'
NEW = 'VidUSB2.rc1'
changed = False
fn = open(NEW, 'w')
for ln in open(OLD):
    if ln.find('FileVersion') >= 0 or ln.find('ProductVersion') >= 0:
        old = ln.rstrip().split(', ')
        if old[1] != verstring:
            print( old[1], verstring )
            changed = True
            fn.write( ', '.join(( old[0], verstring )))
            fn.write( '\n' )
            continue
    fn.write( ln )
fn.close()

if changed:
    print( "Swapping." )
    os.remove( OLD )
    os.rename( NEW, OLD )
else:
    print( "No changes." )
    os.remove( NEW )
