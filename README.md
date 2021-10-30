# PaRappaSource
PaRappa the Rapper Decompilation

## Compiling
The instructions for this should largely be the same as [PSXFunkin](https://github.com/cuckydev/PSXFunkin/blob/master/COMPILE.md) without the iso makes.

You must have a PaRappa the Rapper iso to create a playable iso. Extract the contents to a folder here named iso/, and make sure the XAs and STRs are of 2336-length sectors.

I used jPSXdec to extract the iso contents, which exports XA and STR as 2352-length sectors. There's a tool here ([syncstrip](/tools/syncstrip/syncstrip.c)) that will cut these down to 2336-length sectors.
