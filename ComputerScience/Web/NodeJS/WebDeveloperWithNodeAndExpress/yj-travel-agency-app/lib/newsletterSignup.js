// Newletter Sign up interface
class NewsletterSignup {
  constructor({ name, email }) {
    this.name = name
    this.email = email
  }
  async save() {
    // TODO : save this data to database
  }
}

exports.NewsletterSignup = NewsletterSignup;