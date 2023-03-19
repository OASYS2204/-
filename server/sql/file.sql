DROP TABLE FILES;
CREATE TABLE FILES (
    FCODE SERIAL PRIMARY KEY,
    FNAME VARCHAR(50) NOT NULL,
    OID INT NOT NULL REFERENCES USERS(UID),
    ATTR BIT(11) NOT NULL
);

INSERT INTO  FILES(FNAME, OID, ATTR)
VALUES
('Server', 92023000, B'00111110000'),
('Server/Home', 92023000, B'00111110000'),
('Server/Class', 92023000, B'00111110000'),
('Server/Class/数学Ⅰ', 92023000, B'00111111000'), 
('Server/Class/数学A', 92023000, B'00111111000'),
('Server/Class/ネットワーク概論', 92023000, B'00111111000'), 
('Server/Class/ハードウェア概論', 92023000, B'00111111000'), 
('Server/Class/データベース設計', 92023000, B'00111111000'), 
('Server/Class/C言語', 92023000, B'00111111000'),
('Server/Class/PowerPoint', 92023000, B'00111111000'), 
('Server/Class/Java', 92023000, B'00111111000'),
('Server/Class/SQL', 92023000, B'00111111000'), 
('Server/Class/JSP／Servlet', 92023000, B'00111111000'),
('Server/Class/Excel・Word', 92023000, B'00111111000'), 
('Server/Class/工場原価管理', 92023000, B'00111111000'),
('Server/Class/情報セキュリティ', 92023000, B'00111111000'), 
('Server/Class/ソフトウェア工学', 92023000, B'00111111000'),
('Server/Class/システム設計', 92023000, B'00111111000'), 
('Server/Class/フローチャート', 92023000, B'00111111000'),
('Server/Class/HTML／CSS', 92023000, B'00111111000'), 
('Server/Class/UML', 92023000, B'00111111000'),
('Server/Class/教養英語', 92023000, B'00111111000'), 
('Server/Class/フランス語', 92023000, B'00111111000'), 
('Server/Class/ラテン語', 92023000, B'00111111000'), 
('Server/Class/比較政治学', 92023000, B'00111111000'),
('Server/Class/量子力学', 92023000, B'00111111000'), 
('Server/Class/社会心理学', 92023000, B'00111111000'), 
('Server/Class/マクロ経済学', 92023000, B'00111111000'),
('Server/Class/イギリス文学', 92023000, B'00111111000'), 
('Server/Class/記号論理学', 92023000, B'00111111000');
