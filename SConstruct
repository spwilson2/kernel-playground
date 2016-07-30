import os
from SCons.Script import GlobalContext, StringArray
GlobalContext = GlobalContext()
Export('GlobalContext')

subbuilds   = StringArray()

GLOBALS = {
        'k_src':[],
        'subbuilds':subbuilds
        }

GlobalContext.add_globals(GLOBALS)

def crosstool_path(tool):
    return join_path(TOOL_DIR, TARGET+tool)

# TODO: Logic for deciding the actual target.
TARGET      = 'i686-pc-chronos-'
BUILD_ARCH  = 'i386'
GlobalContext.BUILD_ARCH = BUILD_ARCH

# TODO: Take from the build environment. 
TOOL_DIR 		= os.path.abspath('../tools/bin')

target_sysroot 	= join_path('..', 'sysroot')


# Make the path to the tool os agnostic.

CROSS_CC        = crosstool_path('gcc')
CROSS_LD        = crosstool_path('ld')
CROSS_AS        = crosstool_path('gcc')
CROSS_OBJCOPY   = crosstool_path('objcopy')

HOST_CC         = 'gcc'
HOST_LD         = 'ld'
HOST_AS         = 'gcc'
HOST_OBJCOPY    = 'objcopy'

# TODO: Debug mode, both by config or cli flag.

CCFLAGS = [
         '-ggdb', 
         '-Werror', 
         '-Wall', 
         '-gdwarf-2', 
         '-fno-common',
         '-fno-builtin', 
         '-fno-stack-protector',
         '-DARCH_' + BUILD_ARCH, 
         '-DARCH_STR=' + BUILD_ARCH,
         ]

ASFLAGS = [
       '-ggdb',
       '-Werror',
       '-Wall',
       '-DARCH_' + BUILD_ARCH,
       '-DARCH_STR=' + BUILD_ARCH
       ]

QEMU = 'qemu-system-' + BUILD_ARCH

#FIXME: Ld Builder should be Program
generic_env = Environment()

# Initialize the Callback list builder.
InitCallbackListBuilder(generic_env)

# Example of how to the the Callback list hack
#
# >>> generic_env.AddCall('ls', '-l', 'kernel')
# >>>
# >>> generic_env.AlwaysBuild('FakeTarget')
# >>> generic_env.RunCalls('FakeTarget', None)


host_env = generic_env.Clone(
        CC=HOST_CC,
        LD=HOST_LD,
        OBJCOPY=HOST_OBJCOPY,
        CCFLAGS=CCFLAGS, 
        ASFLAGS=ASFLAGS
        )

cross_env = generic_env.Clone(
        CC=CROSS_CC,
        LD=CROSS_LD,
        OBJCOPY=CROSS_OBJCOPY,
        CCFLAGS=CCFLAGS, 
        ASFLAGS=ASFLAGS
        )


subbuilds   += 'kernel'

num_subbuilds = len(subbuilds)
# Run all other builds recursively through the list.
while num_subbuilds != 0:
    subbuild = subbuilds.pop(len(subbuilds) - 1)
    print('Build: ' + str(subbuild))

    #SConscript(join_path(subbuild,'SConscript'), variant_dir='build', duplicate=0)
    SConscript(join_path(subbuild,'SConscript'), duplicate=0)
    num_subbuilds = len(subbuilds)

for file_ in GLOBALS['k_src']:
    print(file_.rfile())
