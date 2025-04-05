/* MIT License

Copyright (c) 2025 万顷茫然

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// SPDX-License-Identifier: MIT

#include "QJsonConfigurator"
#include <QTest>
#include <QString>
#include <QStringLiteral>
    
class tst_QJsonConfigurator : public QObject
{
    Q_OBJECT
    
public:
    tst_QJsonConfigurator(QObject *parent = 0);
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testTypes();
    
    void testCfgWriteSimple();
    void testCfgWriteNested();
    void testCfgWriteGrouped();
    void testCfgWriteArray();
    
    void testCfgReadSimple();
    void testCfgReadNested();
    void testCfgReadGrouped();
    void testCfgReadArray();
    
private:
    QJsonConfigurator *cfg;
    const TCWA_ENTRIES { 999 };
};

tst_QJsonConfigurator::tst_QJsonConfigurator(QObject *parent) : QObject(parent)
{
}

void tst_QJsonConfigurator::initTestCase()
{
    QString testDataDir { QFileInfo(QFINDTESTDATA("testcfg.json")).absolutePath() };
    if (testDataDir.isEmpty())
        testDataDir = QCoreApplication::applicationDirPath();
    cfg = new QJsonConfigurator(testDataDir + QStringLiteral("/testcfg.json"));
}

void tst_QJsonConfigurator::cleanupTestCase()
{
    delete cfg;
}

void tst_QJsonConfigurator::testTypes()
{
    // Test all types used by JSON
}

void tst_QJsonConfigurator::testCfgWriteSimple()
{
    cfg->setValue("tcws1", 1);
    (*cfg)["tcws2"] = "2";
}

void tst_QJsonConfigurator::testCfgWriteNested()
{
    cfg->setValue("tcwn/first", 1);
    (*cfg)["tcwn/second/third"] = "2";
}

void tst_QJsonConfigurator::testCfgWriteGrouped()
{
    cfg->beginGroup("tcwg");
    cfg->setValue("first", 1);
    (*cfg)["second/third"] = "2";
    cfg->endGroup();
}

void tst_QJsonConfigurator::testCfgWriteArray()
{
    cfg->beginWriteArray("tcwa");
    for (int i = 0; i < TCWA_ENTRIES; ++i) 
    {
        cfg->setArrayIndex(i);
        cfg->setValue("first", 1);
        cfg->setValue("second", 2.);
    }
    cfg->endArray();
}
    
void tst_QJsonConfigurator::testCfgReadSimple()
{
    QCOMPARE(cfg->value("tcws1").toInt(), 1);
    QCOMPARE((*cfg)["tcws1"].toString(), "2");
}

void tst_QJsonConfigurator::testCfgReadNested()
{
    QCOMPARE(cfg->value("tcwn/first").toInt(), 1);
    QCOMPARE((*cfg)["tcwn/second/third"].toString(), "2");
}

void tst_QJsonConfigurator::testCfgReadGrouped()
{
    cfg->beginGroup("tcwg");
    QCOMPARE(cfg->value("first").toInt(), 1);
    QCOMPARE((*cfg)["second/third"].toString(), "2");
    cfg->endGroup();
}

void tst_QJsonConfigurator::testCfgReadArray()
{
    cfg->beginReadArray("tcwa");
    for (int i = 0; i < TCWA_ENTRIES; ++i) 
    {
        cfg->setArrayIndex(i);
        QCOMPARE(cfg->value("first").toInt(), 1);
        QCOMPARE(cfg->value("second").toDouble(), 2.);
    }
    cfg->endArray();
}

QTEST_MAIN(tst_QJsonConfigurator)
#include "tst_QJsonConfigurator.moc"