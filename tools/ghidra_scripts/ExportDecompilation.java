// Write Ghidra's C for every function into <outdir>/<start>_<end>.c, one file per 0x4000-byte chunk of .text.
import java.io.*;
import java.util.*;
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;

public class ExportDecompilation extends GhidraScript {
    @Override
    protected void run() throws Exception {
        File outDir = new File(getScriptArgs()[0]);
        outDir.mkdirs();
        DecompInterface d = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        d.setOptions(opts);
        d.openProgram(currentProgram);
        Map<Long, PrintWriter> files = new HashMap<>();
        int n = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            long a = f.getEntryPoint().getOffset();
            long chunk = a & ~0x3FFFL;
            PrintWriter w = files.get(chunk);
            if (w == null) {
                w = new PrintWriter(new FileWriter(new File(outDir, String.format("%08X.c", chunk))));
                files.put(chunk, w);
            }
            DecompileResults r = d.decompileFunction(f, 60, monitor);
            w.printf("// %s @ 0x%08X size 0x%X%n", f.getName(), a, f.getBody().getNumAddresses());
            if (r.getDecompiledFunction() != null) w.println(r.getDecompiledFunction().getC());
            else w.println("// decompile failed: " + r.getErrorMessage());
            if (++n % 1000 == 0) println("decompiled " + n);
        }
        for (PrintWriter w : files.values()) w.close();
        println("done: " + n + " functions");
    }
}
