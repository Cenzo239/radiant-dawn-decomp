// Set r2/r13 to the small-data base addresses over all code so SDA-relative loads resolve.
import java.math.BigInteger;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.ProgramContext;
import ghidra.program.model.mem.MemoryBlock;

public class SetSdaRegisters extends GhidraScript {
    @Override
    protected void run() throws Exception {
        long sda = currentProgram.getMemory().getBlock(".sdata").getStart().getOffset() + 0x8000;
        long sda2 = currentProgram.getMemory().getBlock(".sdata2").getStart().getOffset() + 0x8000;
        ProgramContext ctx = currentProgram.getProgramContext();
        Register r2 = ctx.getRegister("r2"), r13 = ctx.getRegister("r13");
        for (MemoryBlock b : currentProgram.getMemory().getBlocks()) {
            if (!b.isExecute()) continue;
            ctx.setValue(r2, b.getStart(), b.getEnd(), BigInteger.valueOf(sda2));
            ctx.setValue(r13, b.getStart(), b.getEnd(), BigInteger.valueOf(sda));
        }
        println(String.format("r13=_SDA_BASE_=0x%08X r2=_SDA2_BASE_=0x%08X", sda, sda2));
    }
}
