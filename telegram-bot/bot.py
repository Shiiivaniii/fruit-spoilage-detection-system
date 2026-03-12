from telegram import Update
from telegram.ext import (
ApplicationBuilder,
CommandHandler,
MessageHandler,
ContextTypes,
ConversationHandler,
filters
)

TELEGRAM_TOKEN = "YOUR_BOT_TOKEN"

ASK_FRUIT = 1

async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text(
        "Hello! Use /fruit to enter fruit name or /data to view sensor data."
    )

async def ask_fruit(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text("Enter fruit name:")
    return ASK_FRUIT

async def get_fruit(update: Update, context: ContextTypes.DEFAULT_TYPE):
    fruit = update.message.text
    await update.message.reply_text(f"You entered: {fruit}")
    return ConversationHandler.END

async def data(update: Update, context: ContextTypes.DEFAULT_TYPE):

    temperature = 28.5
    humidity = 64.2
    gas_level = 180

    message = (
        f"Temperature: {temperature} °C\n"
        f"Humidity: {humidity} %\n"
        f"Gas Level: {gas_level}"
    )

    await update.message.reply_text(message)

async def cancel(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text("Operation cancelled.")
    return ConversationHandler.END

def main():

    app = ApplicationBuilder().token(TELEGRAM_TOKEN).build()

    conv_handler = ConversationHandler(
        entry_points=[CommandHandler("fruit", ask_fruit)],
        states={
            ASK_FRUIT: [MessageHandler(filters.TEXT & ~filters.COMMAND, get_fruit)]
        },
        fallbacks=[CommandHandler("cancel", cancel)],
    )

    app.add_handler(CommandHandler("start", start))
    app.add_handler(conv_handler)
    app.add_handler(CommandHandler("data", data))

    print("Bot running...")

    app.run_polling()

if __name__ == "__main__":
    main()