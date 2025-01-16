import { MathOperationsUnavailableError } from './MathOperationsUnavailableError';

interface MathOperationsProxy {
  sum: (a: number, b: number) => number;
  subtract: (a: number, b: number) => number;
  multiply: (a: number, b: number) => number;
  divide: (a: number, b: number) => number;
  addGlobalVariables: () => number;
}

declare global {
    var MathOperationsProxy: MathOperationsProxy;
}

let proxy: MathOperationsProxy;

try {
    const globalProxy = global.MathOperationsProxy as MathOperationsProxy | undefined;
    if (globalProxy == null) {
        throw new Error('global.MathOperationsProxy is not installed! Was the JSI module installed correctly?');
    }

    proxy = globalProxy;
} catch (e) {
    proxy = {
        sum: () => {
            throw new MathOperationsUnavailableError(e);
        },
        subtract: () => {
            throw new MathOperationsUnavailableError(e);
        },
        multiply: () => {
            throw new MathOperationsUnavailableError(e);
        },
        divide: () => {
            throw new MathOperationsUnavailableError(e);
        },
        addGlobalVariables: () => {
            throw new MathOperationsUnavailableError(e);
        },
    };
}

export const MathOperationsProxy = proxy;
