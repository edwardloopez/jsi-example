export type SystemError = 'system/math-operations-unavailable' | 'system/unknown-error';
export type ParameterError = 'parameter/invalid-parameters';

type MathOpsErrorCode = SystemError | ParameterError;

class MathOpsError<TCode extends MathOpsErrorCode> extends Error {
    private readonly _code: TCode;
    private readonly _message: string;

    public get code(): TCode {
        return this._code;
    }

    public get message(): string {
        return this._message;
    }

    constructor(code: TCode, message: string) {
        super(`[${code}]: ${message}`);
        this._code = code;
        this._message = message;
    }

    public toString(): string {
        return `[${this._code}]: ${this._message}`;
    }
}

export class MathOperationsRuntimeError extends MathOpsError<SystemError> {}
