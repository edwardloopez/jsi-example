import { MathOperationsUnavailableError } from './MathOperationsUnavailableError';

interface MathOperationsProxyInterface {
  sum: (a: number, b: number) => number;
  subtract: (a: number, b: number) => number;
  multiply: (a: number, b: number) => number;
  divide: (a: number, b: number) => number;
  addGlobalVariables: () => number;
}

declare global {
  var MathOperationsProxy: MathOperationsProxyInterface | undefined;
}

function getProxy(): MathOperationsProxyInterface {
  const installed = global.MathOperationsProxy;
  if (installed == null) {
    throw new MathOperationsUnavailableError(
      'JSI not installed yet. Was the JSI module installed correctly?',
    );
  }
  return installed;
}

export const MathOperationsProxy: MathOperationsProxyInterface = {
  sum: (a, b) => getProxy().sum(a, b),
  subtract: (a, b) => getProxy().subtract(a, b),
  multiply: (a, b) => getProxy().multiply(a, b),
  divide: (a, b) => getProxy().divide(a, b),
  addGlobalVariables: () => getProxy().addGlobalVariables(),
};
