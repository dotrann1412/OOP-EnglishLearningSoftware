#ifndef RANKINGROW_H
#define RANKINGROW_H

#include <QWidget>
#include <vector>

class RankingRow : public QWidget
{
    Q_OBJECT
public:
    explicit RankingRow(std::string num, std::vector<std::string> row, QWidget *parent = nullptr);

signals:

};

#endif // RANKINGROW_H
