import logging
import sys
import typing


class CustomLogger(logging.Logger):
    def info_overwritable(self, msg: str, *args: str, **kwargs: object) -> None:
        if self.isEnabledFor(logging.INFO):
            kwargs.setdefault("extra", {"_is_overwritable": True})
            self._log(logging.INFO, msg, args, **kwargs, stacklevel=2)


class OverwriteHandler(logging.StreamHandler):
    def __init__(self, stream: typing.TextIO | None = None) -> None:
        super().__init__(stream)
        self.last_caller = None

    def emit(self, record: logging.LogRecord) -> None:
        try:
            msg = self.format(record)
            current_caller = (record.pathname, record.lineno)
            is_overwritable = getattr(record, "_is_overwritable", False)

            if is_overwritable and self.last_caller == current_caller:
                # \x1b[1F - line up \x1b[K - clean line
                self.stream.write(f"\x1b[1F\x1b[K{msg}{self.terminator}")
            else:
                self.stream.write(f"{msg}{self.terminator}")

            self.last_caller = current_caller
            self.flush()
        except Exception:
            self.handleError(record)


def add_debugv_level() -> None:
    DEBUGV_LEVEL_NUM = 9

    def debugv(self: logging.Logger, message: str, *args: str, **kwargs: object) -> None:
        if self.isEnabledFor(DEBUGV_LEVEL_NUM):
            self._log(DEBUGV_LEVEL_NUM, message, args, **kwargs)

    logging.addLevelName(DEBUGV_LEVEL_NUM, "DEBUGV")
    logging.Logger.debugv = debugv


def init_logging(log_level: int) -> None:
    handler = OverwriteHandler(sys.stdout)
    logging.basicConfig(level=log_level, format="%(levelname)s - %(message)s", handlers=[handler])
    logging.setLoggerClass(CustomLogger)

    add_debugv_level()
