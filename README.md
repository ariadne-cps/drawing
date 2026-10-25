# Ariadne Drawing (extraction in progress)

This repository hosts the mathematical drawing adapters and drawing strategies formerly contained in `ariadne-cps/kernel`. It uses `ariadne-cps/kernel` for mathematical types and `ariadne-cps/rendering` for figure/canvas primitives.

**Not yet standalone:** the pinned Kernel revision still compiles these source files itself. The next step is to remove the duplicate implementations and replace drawable inheritance in mathematical classes with value-owning adapters. This branch is not ready for linking or release until that step and independent CI validation complete.

The dependency direction is `drawing -> {kernel, rendering}`. Rendering must not depend on drawing, and the kernel must no longer link drawing after extraction.
