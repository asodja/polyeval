package polyeval;

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v2.managers.engine_interfaces.EngineInterface;

public abstract class PolyKernel extends Kernel {

    protected PolyKernel(KernelParameters parameters) {
        super(parameters);
    }

    abstract EngineInterface getEngineInterface();

}
