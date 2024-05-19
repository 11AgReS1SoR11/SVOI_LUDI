import easyocr
import re
import phonenumbers
import spacy
import sys


def text_recognition(file_path, text_file_name="result.txt"):
    reader = easyocr.Reader(["ru", "en"])
    result = reader.readtext(file_path, detail=0, paragraph=True)  #обработать исключения

    for i in range(len(result)):
        words = result[i].split(" ")
        for j in range(len(words)):
            if (words[j].isupper()):
                words[j] = words[j].lower().capitalize()
        result[i] = " ".join(words)
        result[i] = Dotting(result[i])

    return result #f"Result wrote into {text_file_name}"

def Split_text(list_of_text):
    Words = list() # massive of words
    for i in list_of_text:
        cur_text = re.split(";|,|\n| ", i)
        for j in cur_text:
            Words.append(j)
    return Words

def Take_number(rec_text): # нужен try catch
    Numbers = []
    for text in rec_text:
        for match in phonenumbers.PhoneNumberMatcher(text, "RU"):
            match = phonenumbers.format_number(match.number, phonenumbers.PhoneNumberFormat.INTERNATIONAL)
            Numbers.append(match)
    return Numbers

def Take_email(words):
    Words = words.copy()
    Words.reverse()
    for i in Words:
        if '@' in i:
            return i

def Take_text(Rec_text):
    Words = Split_text(Rec_text)
    Text = " ".join(Words)
    return Text

def Take_Web(Words):
    for i in Words:
        if ('www' in i or "WWW" in i):
            return i
        if (('.ru' in i or '.com' in i) and '@' not in i):
            return i

def Take_FatherName(Words):
    for i in Words:
        i += ' '
        if ("ович " in i or "евич " in i or "ич " in i or "uч " in i or "овна " in i or "евна " in i or "ична " in i or "инична " in i): return i[:-1]
        #if ("ОВИЧ " in i or "ЕВИЧ " in i or "ИЧ " in i or "ОВНА " in i or "ЕВНА " in i or "ИЧНА " in i or "ИНИЧНА " in i): return i

def Take_cityindex(Words):
    for text in Words:
        if (len(text) > 5 and text[0] != '8' and text[0] != '9' and text[0] != '7' and text[0] != '[' and text[0] != '('): # Когда будет лучше распознавание, можно будет убрать
            for i in range(len(text)-5):
                S = text[i] + text[i+1] + text[i+2] + text[i+3] + text[i+4] + text[i+5]
                if (S.isdigit()):
                    return S

def Idx_of_email(text):
    emailidx = text.find(Take_email(text.split(" "))) if Take_email(text.split(" ")) != None else -1
    if ("E-mail" in text): emailidx = text.find("E-mail")
    elif ("mail" in text): emailidx = text.find("mail")
    elif ("Email" in text): emailidx = text.find("Email")
    return emailidx

def Idx_of_number(text):
    number = phonenumbers.PhoneNumberMatcher(text, "RU")
    number_in_text = number.next().start.real - 1 if number.has_next() else -1
    if (" Тел." in text): number_in_text = text.find(" Тел.")
    elif (" тел." in text): number_in_text = text.find(" тел.")
    elif (" тел:" in text):number_in_text = text.find(" тел:")
    elif (" Тел:" in text): number_in_text = text.find(" Тел:")
    elif (" Тел " in text): number_in_text = text.find(" Тел ")
    elif (" тел " in text): number_in_text = text.find(" тел ")
    elif (" т." in text): number_in_text = text.find(" т.")
    elif (" Т." in text): number_in_text = text.find(" Т.")
    elif (" Т:" in text): number_in_text = text.find(" Т:")
    elif (" т:" in text): number_in_text = text.find(" т:")
    elif (" Моб." in text): number_in_text = text.find(" Моб.")
    elif (" моб." in text): number_in_text = text.find(" моб.")
    elif (" Моб:" in text): number_in_text = text.find(" Моб:")
    elif (" моб:" in text): number_in_text = text.find(" моб:")
    elif (" Моб " in text): number_in_text = text.find(" Моб ")
    elif (" моб " in text): number_in_text = text.find(" моб ")
    if (number_in_text == -1): return -1
    else: return number_in_text + 1

#нужно подумать
def Take_org(rec_text):
    text = Take_text(rec_text)
    nlp = spacy.load("en_core_web_sm")
    doc = nlp(text)
    for ent in doc.ents:
        if (ent.label_ == "ORG"):
            return ent.text

def Create_card():
    Card = dict()
    Card["Surname"] = None
    Card["Name"] = None
    Card["FatherName"] = None
    Card["Company"] = None
    Card["Position"] = None
    Card["Number"] = None
    Card["Email"] = None
    Card["Address"] = None
    Card["Web"] = None
    return Card

def Dotting(str):
    str += " "
    str = str.replace(" ru", ".ru")
    str = str.replace(" com", ".com")
    str = str.replace("www ", "www.")
    str = str.replace("wwW ", "www.")
    str = str.replace("Www ", "www.")
    str = str.replace(" @ ", "@")
    str = str.replace("@ ", "@")
    if (str.find(".ru") == -1): str = str.replace("ru ", ".ru ")
    if (str.find(".RU") == -1): str = str.replace("RU ", ".RU ")
    if (str.find(".com") == -1): str = str.replace("com ", ".com ")
    if (str.find("www.") == -1): str = str.replace("www", "www.")
    if (str.find("WWW.") == -1): str = str.replace("WWW", "WWW.")
    return str[:len(str)-1]

def CheckEndAdress(S, emailoradressidx, numberidx):
    if (emailoradressidx != -1 and numberidx != -1):
        return S[:min(numberidx, emailoradressidx) - 1]
    elif (emailoradressidx != -1):
        return S[:emailoradressidx - 1]
    elif (numberidx != -1):
        return S[:numberidx - 1]
    else:
        return S

def Take_adress(Rec_text, email):
    rec_text = Rec_text.copy()
    rec_text.reverse()
    for text in rec_text:
        CitySigns = [[10000," г."], [10000,"город"], [10000,"Санкт"], [10000," ул."], [10000," ул:"], [10000,"Москва"],
                    [10000," Г."], [10000,"Город"], [10000,"санкт"], [10000," Ул."], [10000," Ул:"], [10000," пр."], [10000, "Россия"]]
        if (Take_cityindex(Split_text(rec_text)) != None): CitySigns.append([10000, Take_cityindex(Split_text(rec_text))])
        for i in range(len(CitySigns)):
            CitySigns[i][0] = text.find(CitySigns[i][1])
            if (CitySigns[i][0] == -1): CitySigns[i][0] = 10000
        CitySigns.sort(key=lambda x: x[0])


        if (CitySigns[0][0] != 10000):
            number_in_text = Idx_of_number(text[CitySigns[0][0]:])
            email_in_text = Idx_of_email(text[CitySigns[0][0]:])
            return CheckEndAdress(text[CitySigns[0][0]:], email_in_text, number_in_text)

def NLPName(rec_text):
    FIO = []
    nlp = spacy.load("en_core_web_sm")
    for text in rec_text:
        #doc = nlp(Take_text(text)) # во всё тексте
        doc = nlp(text)
        for ent in doc.ents:
            fio = ent.text.split(" ")
            if (ent.label_ == "PERSON"):
                for name in fio:
                    FIO.append(name)
                    if (len(FIO) == 2):
                        FIO[0], FIO[1] = FIO[1], FIO[0]
                        return FIO

def MYName(rec_text, FatherName):
    FIO = []
    for text in rec_text:
        if (FatherName in text):
            Words = text.split(" ")
            if (Words.index(FatherName) == 1 and len(Words) > 2):
                FIO.append(Words[Words.index(FatherName) + 1])
                FIO.append(Words[Words.index(FatherName) - 1])
                FIO.append(Words[Words.index(FatherName)])
                return FIO
            else:
                FIO.append(Words[Words.index(FatherName) - 2])
                FIO.append(Words[Words.index(FatherName) - 1])
                FIO.append(Words[Words.index(FatherName)])
                return FIO

def Take_name(rec_text):
    FatherName = Take_FatherName(Split_text(rec_text))
    if (FatherName == None): return NLPName(rec_text)
    return MYName(rec_text, FatherName)


def Take_position(Rec_text, lastname, adress):
    for i in Rec_text:
        if (lastname in i):
            i = i[i.index(lastname)+len(lastname) + 1:]
            idxnumber = Idx_of_number(i)
            adressidx = i.find(adress)
            return CheckEndAdress(i, adressidx, idxnumber)

def Vizitka(Rec_text):
    Words = Split_text(Rec_text)
    Card = Create_card()
    Email = Take_email(Words)
    Adress = Take_adress(Rec_text, Email)
    FIO = Take_name(Rec_text)
    lastname = "0943809213"
    if (FIO):
        if (len(FIO) == 3): lastname = FIO[len(FIO) - 1] # с отчеством
        elif (len(FIO) != 0): lastname = FIO[0] # без отчества

        Card["Surname"] = FIO[0] if len(FIO) > 0 else None
        Card["Name"] = FIO[1] if len(FIO) > 1 else None
        Card["FatherName"] = FIO[2] if len(FIO) == 3 else None

    Position = Take_position(Rec_text, lastname, Adress)
    Numbers = Take_number(Rec_text)

    Card["Position"] = Position if Position != '' else None
    Card["Number"] = Numbers
    Card["Email"] = Email
    Card["Web"] = Take_Web(Words)
    Card["Address"] = Adress
    Card["Company"] = Take_org(Rec_text)
    return Card

def main():
    sys.stdout.reconfigure(encoding='utf-8')  # установка кодировки консоли на utf-8
    file_path = ""
    if len(sys.argv) > 1:
        file_path = sys.argv[1]
    else:
        print("Not enough arguments")

    Rec_text = text_recognition(file_path=file_path)
    Card = Vizitka(Rec_text)
    for key, value in Card.items():
        print(key, value, sep=': ')


if __name__ == "__main__":
     main()