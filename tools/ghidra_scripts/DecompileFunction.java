// Print Ghidra's C decompilation of the functions named in the script arguments.
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;

public class DecompileFunction extends GhidraScript {
    @Override
    protected void run() throws Exception {
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        int total = currentProgram.getFunctionManager().getFunctionCount();
        println("functions in program: " + total);
        for (String name : getScriptArgs()) {
            for (Function f : getGlobalFunctions(name)) {
                DecompileResults r = d.decompileFunction(f, 60, monitor);
                println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC() : r.getErrorMessage());
            }
        }
    }
}
