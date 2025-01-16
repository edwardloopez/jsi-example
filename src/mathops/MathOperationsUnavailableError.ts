import { MathOperationsRuntimeError } from '../utils/MathOpsError';

export class MathOperationsUnavailableError extends MathOperationsRuntimeError {
    constructor(reason: unknown) {
        super('system/math-operations-unavailable', `Math operations are unavailable: ${reason}`);
    }
}
